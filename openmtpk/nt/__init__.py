""
    "
    openMTPK Number Theory Module == ==
    == == == == == == == == == == == ==
    =
        The Number Theory Module encapsulates methods related to prime numbers as well as cryptography / encryption algorithms.

                                                                                                         FEATURES: CLASS: Primality -
            Features methods related to prime numbers
                METHODS : is_prime
                              miller_rabin
                                  jacobian_number
                                      solovoy_strassen
                                          mod_pow
                                              carmichael_num
                                                  sieve_of_eratosthenes
                                                      pollard_rho
                                                          ETF

                                                              CLASS : RC4 -
                                                                      Contains methods related to the Rivest - Cipher encryption algo METHODS : byte_swap trad_swap XOR_swap KSA PRGA store_hash compute

                                                                                                                                                    CLASS : Cipher -
                                                                                                                                                            Contains methods related to Caesar Cipher and a Keyword Swap Cipher

                                                                                                                                                                USAGE : >>
                                                                                                                                                                        import openmtpk >> prime_num = openmtpk.nt.primality.is_prime(2999)
                                                                                                                                                                                                           OR >>
                                                                                                                                                                                                       from openmtpk import nt
                                                                                                                                                                                                       ""
                                                                                                                                                                                                       "

                                                                                                                                                                                                       from openmtpk.nt.nt import(
                                                                                                                                                                                                           Primality,
                                                                                                                                                                                                           RC4,
                                                                                                                                                                                                           Cipher, )

                                                                                                                                                                                                           __all__ : list[str] __path__ : list[str]
