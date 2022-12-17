API_DIR			= $(realpath $(CURDIR))
SRC_DIR			= $(API_DIR)/../
MOD_DIR			= $(SRC_DIR)/modules/
INC_DIR			= $(SRC_DIR)/include/

swig_files		= openMTPK.i
run-swig:
	swig -c++ -ocaml -co swigp4.ml
	swig -c++ -ocaml ${swig_files}
	for file in swig.mli swig.ml swigp4.ml ; do swig -c++ -ocaml -co $$file ; done
	swig -ocaml -co swig.mli ; swig -ocaml -co swig.ml
	ocamlc -c swig.mli ; ocamlc -c swig.ml
	ocamlc -I `camlp4 -where` -pp 'camlp4o pa_extend.cmo q_MLast.cmo' -c swigp4.ml
	cp openMTPK_wrap.cxx openMTPK_wrap.c
	ocamlc -c -ccopt -xc++ openMTPK_wrap.c
	ocamlc -c openMTPK.mli
	ocamlc -c openMTPK.ml
final-compile:
	ocamlmktop -custom swig.cmo -I `camlp4 -where` camlp4o.cma swigp4.cmo openMTPK_wrap.o openMTPK.cmo -o example

