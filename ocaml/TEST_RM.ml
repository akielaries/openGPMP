open Printf
open Swig
open RM_pkg

let _ = print_endline "Welcome to RM-pkg's OCaml API."

let repr o = 
    Printf.sprintf "<%s at %#x>" (o -> ":classof" () as string) (o -> "&" () as int)

