program main
  use openMTPK

  integer*8 :: n, p, result

  n = 100
  p = 3
  
  result = _Basics_greatest_power(n, p)
  
  print *, "The greatest power of", p, "that divides", n, "is", result
  
end program

