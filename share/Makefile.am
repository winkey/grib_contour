
www = @WWW@
wwwdisk = @WWWDISK@

pkgdata_DATA = \
	1000hgt.scale \
	200hgt.scale \
	925thk.scale \
	850thk.scale \
	700thk.scale \
	500thk.scale \
	1000rh.scale \
	925rh.scale \
	850rh.scale \
	700rh.scale \
	500rh.scale \
	300rh.scale \
	200rh.scale \
	rain.scale \
	snow.scale \
	frez.scale \
	pellet.scale \
	pwat.scale \
	pop.scale \
	popf.scale \
	popz.scale \
	tstm.scale \
	300wind.scale \
	500wind.scale \
	850wind.scale \
	925wind.scale \
	1000wind.scale \
	200t.scale \
	925t.scale \
	1000t.scale \
	hghtswl.scale \
	perdswl.scale \
	prob17.scale \
	prob25.scale \
	prob32.scale \
	refd.scale \
	maxrefd.scale
	
	
dist_pkgdata_DATA = \
	cape.scale \
	700t.scale \
	300t.scale \
	500t.scale \
	850t.scale \
	1000hgt.scale \
	925hgt.scale \
	850hgt.scale \
	700hgt.scale \
	500hgt.scale \
	300hgt.scale \
	200hgt.scale \
	200wind.scale \
	700wind.scale \
	pmsl.scale \
	pcp.scale \
	prob.scale \
	refd.scale \
	t.scale \
	dp.scale \
	sst.scale \
	ice.scale \
	wind.scale \
	rh.scale \
	hghtww.scale \
	perdww.scale \
	htsgw.scale \
	hghtswl.scale \
	perdswl.scale \
	forecaster.config.sh \
	gfs.config.sh \
	nam_conus.config.sh \
	hrrr.config.sh \
	rap.config.sh \
	nam_ak.config.sh \
	nam_east.config.sh \
	nam_hi.config.sh \
	nam_pr.config.sh \
	nam_west.config.sh \
	windwave.config.sh \
	navgem.config.sh \
	ocean.config.sh \
	ww3.config.sh \
	coamps_cent_am.config.sh \
	coamps_ne_pac.config.sh \
	coamps_w_atl.config.sh \
	coamps_socal.config.sh \
	coamps_cencoos.config.sh \
	ecmwf.config.sh \
	ukmet.config.sh \
	rtma_conus.config.sh \
	rtma_ak.config.sh \
	sst.config.sh


500thk.scale: 500hgt.scale Makefile
	cp $(srcdir)/500hgt.scale $(srcdir)/500thk.scale

700thk.scale: 700hgt.scale Makefile
	cp $(srcdir)/700hgt.scale $(srcdir)/700thk.scale

850thk.scale: 850hgt.scale Makefile
	cp $(srcdir)/850hgt.scale $(srcdir)/850thk.scale

925thk.scale: 925hgt.scale Makefile
	cp $(srcdir)/925hgt.scale $(srcdir)/925thk.scale

%rh.scale: rh.scale Makefile
	cat rh.scale > $@

rain.scale: pcp.scale Makefile
	cp $(srcdir)/pcp.scale $(srcdir)/rain.scale

snow.scale: pcp.scale Makefile
	cp $(srcdir)/pcp.scale $(srcdir)/snow.scale

frez.scale: pcp.scale Makefile
	cp $(srcdir)/pcp.scale $(srcdir)/frez.scale

pellet.scale: pcp.scale Makefile
	cp $(srcdir)/pcp.scale $(srcdir)/pellet.scale

pwat.scale: pcp.scale Makefile
	cp $(srcdir)/pcp.scale $(srcdir)/pwat.scale

pop.scale: prob.scale Makefile
	cp $(srcdir)/prob.scale $(srcdir)/pop.scale

popf.scale: prob.scale Makefile
	cp $(srcdir)/prob.scale $(srcdir)/popf.scale

popz.scale: prob.scale Makefile
	cp $(srcdir)/prob.scale $(srcdir)/popz.scale

tstm.scale: prob.scale Makefile
	cp $(srcdir)/prob.scale $(srcdir)/tstm.scale

300wind.scale: 200wind.scale Makefile
	cp $(srcdir)/200wind.scale $(srcdir)/300wind.scale

500wind.scale: 200wind.scale Makefile
	cp $(srcdir)/200wind.scale $(srcdir)/500wind.scale

850wind.scale: 700wind.scale Makefile
	cp $(srcdir)/700wind.scale $(srcdir)/850wind.scale

925wind.scale: 700wind.scale Makefile
	cp $(srcdir)/700wind.scale $(srcdir)/925wind.scale

1000wind.scale: 700wind.scale Makefile
	cp $(srcdir)/700wind.scale $(srcdir)/1000wind.scale

200t.scale: 300t.scale Makefile
	cp $(srcdir)/300t.scale $(srcdir)/200t.scale

prob17.scale: prob.scale Makefile
	cp $(srcdir)/prob.scale $(srcdir)/prob17.scale

prob25.scale: prob.scale Makefile
	cp $(srcdir)/prob.scale $(srcdir)/prob25.scale

prob32.scale: prob.scale Makefile
	cp $(srcdir)/prob.scale $(srcdir)/prob32.scale

hghtswl.scale: hghtww.scale Makefile
	cp $(srcdir)/hghtww.scale $(srcdir)/hghtswl.scale

perdswl.scale: perdww.scale Makefile
	cp $(srcdir)/perdww.scale $(srcdir)/perdswl.scale

maxrefd.scale: refd.scale Makefile
	cp $(srcdir)/refd.scale $(srcdir)/maxrefd.scale


