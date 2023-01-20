module openMTPK

export ETF, carmichael_num, compute_miller_rabin, derivative_term, greatest_power, is_prime, jacobian_number
export miller_rabin, miller_rabin_prime, mod_pow, op_gcd, pollard_rho, sieve_of_eratosthenes, solovoy_strassen

using CxxWrap
@wrapmodule("jlopenMTPK")

function __init__()
    @initcxx
end

end #module
