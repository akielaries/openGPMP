!/*************************************************************************
! *
! *  Project
! *                         _____ _____  __  __ _____
! *                        / ____|  __ \|  \/  |  __ \
! *  ___  _ __   ___ _ __ | |  __| |__) | \  / | |__) |
! * / _ \| '_ \ / _ \ '_ \| | |_ |  ___/| |\/| |  ___/
! *| (_) | |_) |  __/ | | | |__| | |    | |  | | |
! * \___/| .__/ \___|_| |_|\_____|_|    |_|  |_|_|
! *      | |
! *      |_|
! *
! * Copyright (C) Akiel Aries, <akiel@akiel.org>, et al.
! *
! * This software is licensed as described in the file LICENSE, which
! * you should have received as part of this distribution. The terms
! * among other details are referenced in the official documentation
! * seen here : https://akielaries.github.io/openGPMP/ along with
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
! mtx_routines.f90

!> FORTRAN Subroutine for Matrix Addition on flattened matrices as arrays
!! of type float32. Contains C++ wrapper function
!! @param A Addend A, an array representing a Matrix
!! @param B Addend B, an array representing a Matrix
!! @param C Sum C, an array representing the sum of A + B
!! @param mtx_size Assumes same size M x N
SUBROUTINE mtx_add_routine_float_(A, B, C, mtx_size) bind(C)
    USE :: ISO_FORTRAN_ENV
    USE :: ISO_C_BINDING

    INTEGER, INTENT(IN) :: mtx_size
    REAL(KIND=C_FLOAT), DIMENSION(mtx_size, mtx_size), INTENT(IN) :: A, B
    REAL(KIND=C_FLOAT), DIMENSION(mtx_size, mtx_size), INTENT(OUT) :: C

    C = A + B
END SUBROUTINE mtx_add_routine_float_

!> FORTRAN Subroutine for Matrix Addition on flattened matrices as arrays
!! of type int32. Contains C++ wrapper function
!! @param A Addend A, an array representing a Matrix
!! @param B Addend B, an array representing a Matrix
!! @param C Sum C, an array representing the sum of A + B
!! @param mtx_size Assumes same size M x N
SUBROUTINE mtx_add_routine_int_(A, B, C, mtx_size) bind(C)
    USE :: ISO_FORTRAN_ENV
    USE :: ISO_C_BINDING

    INTEGER, INTENT(IN) :: mtx_size
    INTEGER(C_INT), DIMENSION(mtx_size, mtx_size), INTENT(IN) :: A, B
    INTEGER(C_INT), DIMENSION(mtx_size, mtx_size), INTENT(OUT) :: C

    C = A + B
END SUBROUTINE mtx_add_routine_int_

!> FORTRAN Subroutine for Matrix Multiplication using Fortran intrinsics.
!! Contains C++ wrapper function
!! @param a Multiplier a, an array representing a Matrix
!! @param b Multiplicand b, an array representing a Matrix
!! @param c Product c, an array representing the sum of a + b
!! @param nrows_a Number of rows
!! @param ncols Number of columns
SUBROUTINE Bmtx_mult_routine_int_(A, B, C, nrows1, ncols1, ncols2) bind(C)
    USE :: ISO_FORTRAN_ENV
    USE :: ISO_C_BINDING

    implicit none
    INTEGER, INTENT(IN) :: nrows1, ncols1, ncols2
    REAL, INTENT(IN) :: A(nrows1, ncols1), B(ncols1, ncols2)
    REAL, INTENT(OUT) :: C(nrows1, ncols2)
    INTEGER :: i, j, k

    ! Perform matrix multiplication
    do i = 1, nrows1
        do j = 1, ncols2
            C(i, j) = 0
            do k = 1, ncols1
                C(i, j) = C(i, j) + A(i, k)*B(k, j)
            end do
        end do
    end do
END SUBROUTINE Bmtx_mult_routine_int_

SUBROUTINE mtx_mult_routine_int_(A, B, C, mtx_size) bind(C)
    USE :: ISO_FORTRAN_ENV
    USE :: ISO_C_BINDING

    INTEGER, INTENT(IN) :: mtx_size
    INTEGER(KIND=C_INT), DIMENSION(mtx_size, mtx_size), INTENT(IN) :: A, B
    INTEGER(KIND=C_INT), DIMENSION(mtx_size, mtx_size), INTENT(OUT) :: C

    INTEGER :: i, j, k

    ! Perform matrix multiplication
    DO i = 1, mtx_size
        DO j = 1, mtx_size
            C(i, j) = 0
            DO k = 1, mtx_size
                C(i, j) = C(i, j) + A(i, k) * B(k, j)
            END DO
        END DO
    END DO
END SUBROUTINE mtx_mult_routine_int_

