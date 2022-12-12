# Example using RM-pkg's R API

dyn.load(paste("lib/RM_pkg", .Platform$dynlib.ext, sep=""))
source("lib/RM_pkg.R")

out <- "Welcome to RM-pkg's R API."
print(out)

