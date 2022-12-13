API_DIR			= $(realpath $(CURDIR))
SRC_DIR			= $(API_DIR)/../
MOD_DIR			= $(SRC_DIR)/modules/
INC_DIR			= $(SRC_DIR)/include/

swig_files		= RM_pkg.i
run-swig:
	swig -c++ -ocaml -co swigp4.ml
	swig -c++ -ocaml ${swig_files}
	for file in swig.mli swig.ml swigp4.ml ; do swig -c++ -ocaml -co $$file ; done
	swig -ocaml -co swig.mli ; swig -ocaml -co swig.ml
	ocamlc -c swig.mli ; ocamlc -c swig.ml
	ocamlc -I `camlp4 -where` -pp 'camlp4o pa_extend.cmo q_MLast.cmo' -c swigp4.ml
	cp RM_pkg_wrap.cxx RM_pkg_wrap.c
	ocamlc -c -ccopt -xc++ RM_pkg_wrap.c
	ocamlc -c RM_pkg.mli
	ocamlc -c RM_pkg.ml
final-compile:
	ocamlmktop -custom swig.cmo -I `camlp4 -where` camlp4o.cma swigp4.cmo RM_pkg_wrap.o RM_pkg.cmo -o example

