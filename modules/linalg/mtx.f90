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


!> FORTRAN Subroutine for Matrix Addition. Contains C++ wrapper
!! function 
!! @param a Addend a, an array representing a Matrix
!! @param b Addend b, an array representing a Matrix
!! @param c Sum c, an array representing the sum of a + b
!! @param nrows Number of rows
!! @param ncols Number of columns
subroutine mtx_add(a, b, c, nrows, ncols)
  !implicit none
  !< Using 64-bit (8-byte) width for numeric types 
  !integer(kind=8), intent(in) :: nrows, ncols
  !real(kind=8), intent(in) :: a(nrows, ncols), b(nrows, ncols)
  !real(kind=8), intent(out) :: c(nrows, ncols)
  !integer(kind=8) :: i, j

  !do i = 1, nrows
  !  do j = 1, ncols
  !    c(i, j) = a(i, j) + b(i, j)
  !  end do
  !end do
  implicit none
  !< Using 64-bit (8-byte) width for numeric types 
  integer(kind=8), intent(in) :: nrows, ncols
  real(kind=8), intent(in) :: a(nrows, ncols), b(nrows, ncols)
  real(kind=8), intent(out) :: c(nrows, ncols)
  integer(kind=8) :: i, j

  do i = 1, nrows
    do j = 1, ncols, 128
      c(i, j)   = a(i, j)   + b(i, j)
      c(i, j+1) = a(i, j+1) + b(i, j+1)
      c(i, j+2) = a(i, j+2) + b(i, j+2)
      c(i, j+3) = a(i, j+3) + b(i, j+3)
    end do
  end do

end subroutine mtx_add

subroutine mtxx_add(A, B, C, size)
    integer(kind=8), intent(in) :: A(:,:), B(:,:)
    integer(kind=8), intent(out) :: C(:,:)
    integer(kind=8), intent(in) :: size
    integer(kind=8) :: i, j

    do i = 1, size
        do j = 1, size, 4
            C(i,j)   = A(i,j)   + B(i,j)
            C(i,j+1) = A(i,j+1) + B(i,j+1)
            C(i,j+2) = A(i,j+2) + B(i,j+2)
            C(i,j+3) = A(i,j+3) + B(i,j+3)
        end do
    end do

end subroutine mtxx_add


!> FORTRAN Subroutine for Matrix Multiplication using Fortran intrinsics. 
!! Contains C++ wrapper function
!! @param a Multiplier a, an array representing a Matrix
!! @param b Multiplicand b, an array representing a Matrix
!! @param c Product c, an array representing the sum of a + b
!! @param nrows_a Number of rows
!! @param ncols Number of columns
subroutine mtx_mult(matrix1, matrix2, result, nrows1, ncols1, ncols2)
  implicit none
  integer, intent(in) :: nrows1, ncols1, ncols2
  real, intent(in) :: matrix1(nrows1, ncols1), matrix2(ncols1, ncols2)
  real, intent(out) :: result(nrows1, ncols2)
  integer :: i, j, k

  ! Perform matrix multiplication
  do i = 1, nrows1
    do j = 1, ncols2
      result(i, j) = 0.0
      do k = 1, ncols1
        result(i, j) = result(i, j) + matrix1(i, k) * matrix2(k, j)
      end do
    end do
  end do
end subroutine mtx_mult

