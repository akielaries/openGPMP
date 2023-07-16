# Julia is not inherently an Object-Oriented Programming Languages,
# however, the source C++ code makes use of namespaces and classes.
# In openGPMP, each Class of and its encapsulated method are housed 
# in an overarching namespace `gpmp`. Thus to use methods of a given
# class use this syntax:
#   
#   gpmp!<Class Name>
#
# So for the class `Basics` that houses the method greatest_power
# we would call it with:
#   
#   obj = openGPMP.gpmp!Basics()
#   res = greatest_power(obj, 3, 5)
# 
# Notice how we pass in the class "object" as a parameter to the 
# greatest power method.

#Import openGPMP as a module
using openGPMP
a, b = 15, 5

# declare an "object" from the source C++ Basics Class
basics = openGPMP.gpmp!Basics()
result = op_gcd(basics, a, b)

println(result)

