/*****************************************************************************
ported to c by Brian Case rush@winkey.org 12-12-2008
*****************************************************************************/
/*****************************************************************************
* $Id: gdal_merge.py 12993 2007-11-24 19:22:11Z hobu $
*
* Project:  InSAR Peppers
* Purpose:  Module to extract data from many rasters into one output.
* Author:   Frank Warmerdam, warmerdam@pobox.com
*
*****************************************************************************/
/* Copyright (c) 2000, Atlantis Scientific Inc. (www.atlsci.com)
* 
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Library General Public
* License as published by the Free Software Foundation; either
* version 2 of the License, or (at your option) any later version.
* 
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Library General Public License for more details.
* 
* You should have received a copy of the GNU Library General Public
* License along with this library; if not, write to the
* Free Software Foundation, Inc., 59 Temple Place - Suite 330,
* Boston, MA 02111-1307, USA.
*****************************************************************************/
#define _ISOC99_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <math.h>
#include <gdal.h>

#include "error.h"
#include "options.h"
#include "grib.h"
#include <ogr_srs_api.h>
#include "gdalcode.h"
#include "merge.h"

#define DEBUG 1


/******************************************************************************/

typedef struct {
	double urx;
	double ury;
	double llx;
	double lly;
} corners;

typedef struct {
	GDALDatasetH ds;
	int bands;
	int xsize;
	int ysize;
	GDALDataType band_type;
	const char *projection;
	double geotransform[6];
	corners c;
	GDALColorTableH ct;
} file_info;


/******************************************************************************/
int raster_copy_with_nodata(
	GDALDatasetH s_fh,
	int s_xoff,
	int s_yoff,
	int s_xsize,
	int s_ysize,
	int s_band_n,
	GDALDatasetH t_fh,
	int t_xoff,
	int t_yoff,
	int t_xsize,
	int t_ysize,
	int t_band_n,
  double nodata)
{
	
	if (DEBUG) {
		printf("raster_copy_with_nodata %d,%d,%d,%d to %d,%d,%d,%d.\n",
					 s_xoff, s_yoff, s_xsize, s_ysize,
					 t_xoff, t_yoff, t_xsize, t_ysize);
	}
	
	GDALRasterBandH s_band = get_band(s_fh, s_band_n);
	GDALRasterBandH t_band = get_band(t_fh, t_band_n);
	
	GDALDataType dtype = GDALGetRasterDataType(t_band);
	
	/* alocate memory */
	
	char *sdata;
	size_t dsize = GDALGetDataTypeSize(dtype);
	
		if (!(sdata = malloc(t_xsize * t_ysize * dsize / 8 + 1))) {
		printf("ERROR allocating memory\n");
		exit(EXIT_FAILURE);
	}
	
	char *tdata;
	
	if (!(tdata = malloc(t_xsize * t_ysize * dsize / 8 + 1))) {
		printf("ERROR allocating memory\n");
		exit(EXIT_FAILURE);
	}
	
	/* read the data */
	
	GDALRasterIO  (s_band, GF_Read,
								 s_xoff, s_yoff,
								 s_xsize, s_ysize,
								 sdata,
								 t_xsize, t_ysize,
								 dtype,
								 0, 0);
	
	GDALRasterIO  (t_band, GF_Read,
								 t_xoff, t_yoff,
								 t_xsize, t_ysize,
								 tdata,
								 t_xsize, t_ysize,
								 dtype,
								 0, 0);
	
	size_t i;
	
	switch(dtype) {
		case GDT_Byte:
			for (i = 0; i < t_xsize * t_ysize ; i++) {
				if (((GByte *)sdata)[i] == nodata && ((GByte *)tdata)[i] != nodata)
					((GByte *)sdata)[i] = ((GByte *)tdata)[i];
			}
			break;
		case GDT_Float32:
			for (i = 0; i < t_xsize * t_ysize ; i++) {
				if (((float *)sdata)[i] == nodata && ((float *)tdata)[i] != nodata)
					((float *)sdata)[i] =((float *)tdata)[i];
			}
			break;
		case GDT_Float64:
			for (i = 0; i < t_xsize * t_ysize ; i++) {
				if (((double *)sdata)[i] == nodata && ((double *)tdata)[i] != nodata)
					((double *)sdata)[i] = ((double *)tdata)[i];
			}
			break;
		case GDT_Int32:
			for (i = 0; i < t_xsize * t_ysize ; i++) {
				if (((GInt32 *)sdata)[i] == nodata && ((GInt32 *)tdata)[i] != nodata)
					((GInt32 *)sdata)[i] = ((GInt32 *)tdata)[i];
			}
		case GDT_UInt16:
			for (i = 0; i < t_xsize * t_ysize ; i++) {
				if (((GUInt16 *)sdata)[i] == nodata && ((GUInt16 *)tdata)[i] != nodata)
					((GUInt16 *)sdata)[i] = ((GUInt16 *)tdata)[i];
			}
			break;
		case GDT_Int16:
			for (i = 0; i < t_xsize * t_ysize ; i++) {
				if (((GInt16 *)sdata)[i] == nodata && ((GInt16 *)tdata)[i] != nodata)
					((GInt16 *)sdata)[i] = ((GInt16 *)tdata)[i];
			}
			break;
		case GDT_UInt32:
			for (i = 0; i < t_xsize * t_ysize ; i++) {
				if (((GUInt32 *)sdata)[i] == nodata && ((GUInt32 *)tdata)[i] != nodata)
					((GUInt32 *)sdata)[i] = ((GUInt32 *)tdata)[i];
			}
			break;
		case GDT_CInt16:
			for (i = 0; i < t_xsize * t_ysize ; i++) {
				if (((GInt16 *)sdata)[i * 2] == nodata && ((GInt16 *)tdata)[i * 2] != nodata)
					((GInt16 *)sdata)[i * 2] = ((GInt16 *)tdata)[i * 2];
			}
			break;
		case GDT_CInt32:
			for (i = 0; i < t_xsize * t_ysize ; i++) {
				if (((GInt32 *)sdata)[i * 2] == nodata && ((GInt32 *)tdata)[i * 2] != nodata)
					((GInt32 *)sdata)[i * 2] = ((GInt32 *)tdata)[i * 2];
			}
			break;
		case GDT_CFloat32:
			for (i = 0; i < t_xsize * t_ysize ; i++) {
				if (((float *)sdata)[i * 2] == nodata && ((float *)tdata)[i * 2] != nodata)
					((float *)sdata)[i * 2] =((float *)tdata)[i * 2];
			}
			break;
		case GDT_CFloat64:
			for (i = 0; i < t_xsize * t_ysize ; i++) {
				if (((double *)sdata)[i * 2] == nodata && ((double *)tdata)[i * 2] != nodata)
					((double *)sdata)[i * 2] = ((double *)tdata)[i * 2];
			}
			break;
		default:
			break;
	}
	/* write the data */
	
	GDALRasterIO  (t_band, GF_Write,
								 t_xoff, t_yoff,
								 t_xsize, t_ysize,
								 sdata,
								 t_xsize, t_ysize,
								 dtype,
								 0, 0);
	
	free(sdata);
	free(tdata);
	
/*#warning fixme
	
	use casts to parse the data for nodata
	
	
    data_src = s_band.ReadAsArray( s_xoff, s_yoff, s_xsize, s_ysize,
                                   t_xsize, t_ysize )
    data_dst = t_band.ReadAsArray( t_xoff, t_yoff, t_xsize, t_ysize )

    nodata_test = Numeric.equal(data_src,nodata)
    to_write = Numeric.choose( nodata_test, (data_src, data_dst) )
                               
    t_band.WriteArray( to_write, t_xoff, t_yoff )
*/
	return 0;
}

/******************************************************************************/
int raster_copy(
	GDALDatasetH s_fh,
	int s_xoff,
	int s_yoff,
	int s_xsize,
	int s_ysize,
	int s_band_n,
	GDALDatasetH t_fh,
	int t_xoff,
	int t_yoff,
	int t_xsize,
	int t_ysize,
	int t_band_n,
  double nodata)
{
	
	if (!isnan(nodata)) {
		return raster_copy_with_nodata(s_fh, s_xoff, s_yoff,
																	 s_xsize, s_ysize, s_band_n,
																	 t_fh, t_xoff, t_yoff,
																	 t_xsize, t_ysize, t_band_n,
																	 nodata);
	}
	
	if (DEBUG) {
		printf("raster_copy %d,%d,%d,%d to %d,%d,%d,%d.\n",
					 s_xoff, s_yoff, s_xsize, s_ysize,
					 t_xoff, t_yoff, t_xsize, t_ysize);
	}

	GDALRasterBandH s_band = get_band(s_fh, s_band_n);
	GDALRasterBandH t_band = get_band(t_fh, t_band_n);
	
	GDALDataType dtype = GDALGetRasterDataType(t_band);
	
	/* alocate memory */
	
	char *data;
	size_t dsize = GDALGetDataTypeSize(dtype);
	
	if (!(data = malloc(t_xsize * t_ysize * dsize / 8 + 1))) {
		printf("ERROR allocating memory\n");
		exit(EXIT_FAILURE);
	}
	
	/* read the data */
	
	GDALRasterIO  (s_band, GF_Read,
								 s_xoff, s_yoff,
								 s_xsize, s_ysize,
								 data,
								 t_xsize, t_ysize,
								 dtype,
								 0, 0);
	
	/* write the data */
	
	
	GDALRasterIO  (t_band, GF_Write,
								 t_xoff, t_yoff,
								 t_xsize, t_ysize,
								 data,
								 t_xsize, t_ysize,
								 dtype,
								 0, 0);
	
	free(data);
	
	return 0;
}



/******************************************************************************/
int init_from_dataset(file_info *fi, GDALDatasetH ds) {
	/*
	Initialize file_info from dataset
	*/
	
	fi->ds = ds;
	fi->bands = GDALGetRasterCount(ds);
	fi->xsize = GDALGetRasterXSize(ds);
	fi->ysize = GDALGetRasterYSize(ds);
	
	GDALRasterBandH band = get_band(ds, 1);
	
	fi->band_type = GDALGetRasterDataType(band);
	
	fi->projection = GDALGetProjectionRef(ds);

	GDALGetGeoTransform(ds, fi->geotransform);
	
	fi->c.llx = fi->geotransform[0];
	fi->c.lly = fi->geotransform[3];
	fi->c.urx = fi->c.llx + (fi->geotransform[1] * (fi->xsize));
	fi->c.ury = fi->c.lly + (fi->geotransform[5] * (fi->ysize));
		printf("LL:(%lg,%lg)   UR:(%lg,%lg)\n",
				 fi->c.llx, fi->c.lly,
				 fi->c.urx, fi->c.ury);
	fi->ct = GDALGetRasterColorTable (band);
	
	return 1;
}

/******************************************************************************/
void datasets_to_fileinfos(file_info *file_infos, GDALDatasetH *datasets) {
	/*
	Translate a list of GDAL filenames, into file_info objects.

	names -- list of valid GDAL dataset names.

	Returns a list of file_info objects.  There may be less file_info objects
	than names if some of the names could not be opened as GDAL files.
	*/
	GDALDatasetH *ds;
	file_info *fi = file_infos;
	
	for (ds = datasets ; *ds ; ds++) {
		if (init_from_dataset(fi, *ds))
			fi++;
	}
	
	return;
}

/******************************************************************************/
void report(file_info *fi) {
	printf("File Size: %dx%dx%d\n", fi->xsize, fi->ysize, fi->bands);
	printf("Pixel Size: %lg x %lg\n", fi->geotransform[1], fi->geotransform[5]);
	printf("LL:(%lg,%lg)   UR:(%lg,%lg)\n",
				 fi->c.llx, fi->c.lly,
				 fi->c.urx, fi->c.ury);
	
	return;
}

/******************************************************************************/
int fi_copy_into(file_info *fi,
								 GDALDatasetH t_fh,
								 corners c,
								 int s_band,
								 int t_band,
								 double nodata_arg)
{
	/*
	Copy this files image into target file.
	
	This method will compute the overlap area of the file_info objects
	file, and the target gdal.Dataset object, and copy the image data
	for the common window area.  It is assumed that the files are in
	a compatible projection ... no checking or warping is done.  However,
	if the destination file is a different resolution, or different
	image pixel type, the appropriate resampling and conversions will
	be done (using normal GDAL promotion/demotion rules).
	
	t_fh -- gdal.Dataset object for the file into which some or all
	of this file may be copied.
	
	Returns 1 on success (or if nothing needs to be copied), and zero one
	failure.
	*/
	
	double t_geotransform[6];
	corners tw;
	int tw_xoff;
	int tw_yoff;
	int tw_xsize;
	int tw_ysize;
	int sw_xoff;
	int sw_yoff;
	int sw_xsize;
	int sw_ysize;
	
	GDALGetGeoTransform(t_fh, t_geotransform);


	/* figure out intersection region */
	tw.llx = MAX(c.llx, fi->c.llx);
	tw.urx = MIN(c.urx, fi->c.urx);
	if (t_geotransform[5] > 0) {
		tw.lly = MAX(c.lly, fi->c.lly);
		tw.ury = MIN(c.ury, fi->c.ury);
	}
	else {
		tw.lly = MIN(c.lly, fi->c.lly);
		tw.ury = MAX(c.ury, fi->c.ury);
	}
  
	/* do they even intersect? */
	if (tw.llx >= tw.urx)
		return 1;
	
	if (t_geotransform[5] < 0 && tw.lly <= tw.ury)
		return 1;
	
	if (t_geotransform[5] > 0 && tw.lly >= tw.ury)
		return 1;
      
	/* compute target window in pixel coordinates. */
	tw_xoff = ((tw.llx - t_geotransform[0]) / t_geotransform[1] + 0.1);
	tw_yoff = ((tw.lly - t_geotransform[3]) / t_geotransform[5] + 0.1);
	tw_xsize = ((tw.urx - t_geotransform[0])/t_geotransform[1] + 0.5) - tw_xoff;
	tw_ysize = ((tw.ury - t_geotransform[3])/t_geotransform[5] + 0.5) - tw_yoff;

	fprintf(stderr, "Target Window LL:(%lg,%lg)   UR:(%lg,%lg)\n",
					tw.llx, tw.lly, tw.urx, tw.ury);
	fprintf(stderr, "Target Window off:(%i,%i)   size:(%i,%i)\n",
					tw_xoff, tw_yoff, tw_xsize, tw_ysize);
	
	if (tw_xsize < 1 || tw_ysize < 1)
		return 1;

/* Compute source window in pixel coordinates. */
	sw_xoff = ((tw.llx - fi->geotransform[0]) / fi->geotransform[1]);
	sw_yoff = ((tw.lly - fi->geotransform[3]) / fi->geotransform[5]);
	sw_xsize = ((tw.urx - fi->geotransform[0]) / fi->geotransform[1] + 0.5) - sw_xoff;
	sw_ysize = ((tw.ury - fi->geotransform[3]) / fi->geotransform[5] + 0.5) - sw_yoff;
	
	fprintf(stderr, "Source Window off:(%i,%i)   size:(%i,%i)\n",
					sw_xoff, sw_yoff, sw_xsize, sw_ysize);

	if (sw_xsize < 1 || sw_ysize < 1)
		return 1;
	
	/* copy the selected region. */
	return raster_copy(fi->ds, sw_xoff, sw_yoff,
										 sw_xsize, sw_ysize, s_band,
										 t_fh, tw_xoff, tw_yoff,
										 tw_xsize, tw_ysize, t_band,
										 nodata_arg);
	
	return 0;
}

/*******************************************************************************
main function to merge multiple datasets into one

args:
					datasets		GDALDatasetH array of the datasets to merge
											terminated with a null

returns:
					GDALDatasetH for the merged data

notes: 		all datasets must be closed
					exit() on error
*******************************************************************************/

GDALDatasetH merge(GDALDatasetH *datasets,
									int missing,
									double missing_value)
{
	
	file_info file_infos[100] = {};
	file_info *fi = file_infos;
	
	char *format = "MEM";
	char *out_file = "somememfile";
	
	corners c = {};
	
	double psize_x;
	double psize_y;
	
	int xsize;
	int ysize;

	double nodata = NAN;
  
	char *create_options[100] = {};
	
	double pre_init = NAN;
	GDALDataType band_type = GDT_Unknown;
	
	
	int bands;
	
	
	GDALDatasetH t_fh;
	
	if (missing) {
		nodata = missing_value;
		pre_init = missing_value;
	}
		
	GDALDriverH Driver = GDALGetDriverByName("MEM");
	
	if (!Driver) {
		fprintf(stderr, "Format driver %s not found, pick a supported driver.\n",
						format);
		exit(EXIT_FAILURE);
	}
	
	/* Collect information on all the source files. */
	datasets_to_fileinfos(file_infos, datasets);
	
	c.llx = file_infos[0].c.llx;
	c.lly = file_infos[0].c.lly;
	c.urx = file_infos[0].c.urx;
	c.ury = file_infos[0].c.ury;
	
	for (fi = file_infos + 1; fi->ds ; fi++) {
		c.llx = MIN(c.llx, fi->c.llx);
		c.lly = MIN(c.lly, fi->c.lly);
		c.urx = MAX(c.urx, fi->c.urx);
		c.ury = MAX(c.ury, fi->c.ury);
	}
	
	psize_x = file_infos[0].geotransform[1];
	psize_y = file_infos[0].geotransform[5];
	
	band_type = file_infos[0].band_type;
	
	/* Create output file if it does not already exist. */
	
	double geotransform[6] = {c.llx, psize_x, 0, c.lly, 0, psize_y};

	xsize = ((c.urx - c.llx) / geotransform[1] + 0.5);
	ysize = ((c.ury - c.lly) / geotransform[5] + 0.5);
	
	xsize = abs(xsize);
	ysize = abs(ysize);

	bands = file_infos[0].bands;
	
	if (DEBUG) {
		fprintf(stderr, "Target LL:(%lg,%lg)   UR:(%lg,%lg)\n",
						c.llx, c.lly, c.urx, c.ury);
		fprintf(stderr, "target File Size: %dx%dx%d\n", xsize, ysize, bands);
		//fprintf(stderr, "Target projection: %s\n", GDALGetProjectionRef(t_fh));
		fprintf(stderr, "Target geotrandform:\n");
		fprintf(stderr, "                     Origin = (%.15f,%.15f)\n",
						geotransform[0], geotransform[3]);
		fprintf(stderr, "                     Pixel Size = (%.15f,%.15f)\n",
						geotransform[1], geotransform[5]);
		fprintf(stderr, "                     Rotation = (%.15f,%.15f)\n",
						geotransform[2], geotransform[4]);
	}
	
	t_fh = GDALCreate(Driver, out_file, xsize, ysize,
										bands, band_type, create_options);
		
	if (!t_fh)
		ERROR("Creation failed, terminating merge.\n");
		
	GDALSetGeoTransform(t_fh, geotransform);
	GDALSetProjection(t_fh, file_infos[0].projection);

	/* Do we need to pre-initialize the whole mosaic file to some value? */
	if (!isnan(pre_init)) {
		int b;
		GDALRasterBandH band;
		
		for (b = 1 ; b < bands ; b++) {
			band = GDALGetRasterBand(t_fh, b);
      GDALFillRaster (band, pre_init, 0.0);
		}
	}

	/* Copy data from source files into output file. */
	
	for (fi = file_infos ; fi->ds ; fi++) {
		int band = 1;
		if (DEBUG)
			report(fi);
		
		for (band = 1 ; band < bands + 1 ; band++) {
			
			fi_copy_into(fi, t_fh, c, band, band, nodata);
		}
	}
	
	return t_fh;
}
