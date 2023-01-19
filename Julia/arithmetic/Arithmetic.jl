module Arithmetic

export greatest_power, op_gcd

using CxxWrap
@wrapmodule("jlArithmetic")

function __init__()
    @initcxx
end

end #module
