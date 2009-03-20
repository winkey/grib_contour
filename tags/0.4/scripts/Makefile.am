
bin_SCRIPTS = generic.sh \
	gfs.sh \
	nam_west.sh \
	nam_east.sh \
	nam_hi.sh \
	nam_ak.sh \
	nam_pr.sh


CLEANFILES = $(bin_SCRIPTS)

EXTRA_DIST = generic.in \
	gfs.in \
	nam_west.in \
	nam_east.in \
	nam_hi.in \
	nam_ak.in \
	nam_pr.in

dist_bin_SCRIPTS = generic.sh \
	gfs.sh \
	nam_west.sh \
	nam_east.sh \
	nam_hi.sh \
	nam_ak.sh \
	nam_pr.sh

   
do_subst = sed -e 's,[@]bindir[@],$(bindir),g'
     
generic.sh: generic.in Makefile
	$(do_subst) < $(srcdir)/generic.in > generic.sh
	chmod +x generic.sh

gfs.sh: gfs.in Makefile
	$(do_subst) < $(srcdir)/gfs.in > gfs.sh
	chmod +x gfs.sh

nam_west.sh: nam_west.in Makefile
	$(do_subst) < $(srcdir)/nam_west.in > nam_west.sh
	chmod +x nam_west.sh

nam_east.sh: nam_east.in Makefile
	$(do_subst) < $(srcdir)/nam_east.in > nam_east.sh
	chmod +x nam_east.sh

nam_hi.sh: nam_hi.in Makefile
	$(do_subst) < $(srcdir)/nam_hi.in > nam_hi.sh
	chmod +x nam_hi.sh

nam_ak.sh: nam_ak.in Makefile
	$(do_subst) < $(srcdir)/nam_ak.in > nam_ak.sh
	chmod +x nam_ak.sh

nam_pr.sh: nam_pr.in Makefile
	$(do_subst) < $(srcdir)/nam_pr.in > nam_pr.sh
	chmod +x nam_pr.sh


## File created by the gnome-build tools
