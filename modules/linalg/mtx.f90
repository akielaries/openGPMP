!/*************************************************************************
! *
! *  Project
! *                        __  __ _______ _____  _  __
! *                       |  \/  |__   __|  __ \| |/ /
! *  ___  _ __   ___ _ __ | \  / |  | |  | |__) | ' /
! * / _ \| '_ \ / _ \ '_ \| |\/| |  | |  |  ___/|  <
! *| (_) | |_) |  __/ | | | |  | |  | |  | |    | . \
! * \___/| .__/ \___|_| |_|_|  |_|  |_|  |_|    |_|\_\
! *      | |
! *      |_|
! *
! *
! * Copyright (C) Akiel Aries, <akiel@akiel.org>, et al.
! *
! * This software is licensed as described in the file LICENSE, which
! * you should have received as part of this distribution. The terms
! * among other details are referenced in the official documentation
! * seen here : https://akielaries.github.io/openMTPK/ along with
! * important files seen in this project.
! *
! * You may opt to use, copy, modify, merge, publish, distribute
! * and/or sell copies of the Software, and permit persons to whom
! * the Software is furnished to do so, under the terms of the
! * LICENSE file. As this is an Open Source effort, all implementations
! * must be of the same methodology.
! *
! *
! *
! * This software is distributed on an AS IS basis, WITHOUT
! * WARRANTY OF ANY KIND, either express or implied.
! *
! ************************************************************************/


!< FORTRAN Subroutine for Matrix Addition. Contains C++ wrapper
!! function 
!< @param a Addend a, an array representing a Matrix
!< @param b Addend b, an array representing a Matrix
!< @param c Sum c, an array representing the sum of a + b
!< @param nrows Number of rows
!< @param ncols Number of columns
subroutine mtx_add(a, b, c)!, nrows, ncols)
  implicit none
  !< Using 64-bit width for numeric types 
  integer(kind=8) :: nrows, ncols
  real(kind=8), intent(in) :: a(nrows, ncols), b(nrows, ncols)
  real(kind=8), intent(out) :: c(nrows, ncols)
  integer(kind=8) :: i, j
  nrows = size(a, 1)
  ncols = size(a, 2)


  do i = 1, nrows
    do j = 1, ncols
      c(i, j) = a(i, j) + b(i, j)
    end do
  end do

end subroutine mtx_add

!< FORTRAN Subroutine for Matrix Addition. Contains C++ wrapper
!! function 
!< @param a Addend a, an array representing a Matrix
!< @param b Addend b, an array representing a Matrix
!< @param c Sum c, an array representing the sum of a + b
!< @param nrows Number of rows
!< @param ncols Number of columns
!subroutine mtx_mult(a, b, c, nrows_a, ncols_A)


!end subroutine mtx_mult
