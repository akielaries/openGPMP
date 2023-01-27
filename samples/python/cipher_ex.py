#!/ usr / bin / python3
from openmtpk import nt

    def
    main()
    : c = nt.Cipher()
              ciph = c.caesar('Plaintext', 5)
                         print(ciph)

                             ciph_1 = c.caesar('ATTACKATONCE', 4)
                                          print(ciph_1)

                                              text = "Password" shift = "Computer" encoded_text = c.keyword_encode(shift)
                                                                                                      hashtext = c.keyword(
                                                                                                          text, encoded_text)
                                                                                                                     print(
                                                                                                                         hashtext)

                                                                                                                         if __name__
                                                                                                                 == '__main__' : main()
