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
!! @param A Multiplier A, an array representing a Matrix
!! @param B Multiplicand B, an array representing a Matrix
!! @param C Product C, an array representing the produce Matrix
!! @param rows_a Number of rows Matrix A
!! @param cols_a Number of columns Matrix A
!! @param cols_b Number of columns Matrix B
SUBROUTINE mtx_mult_routine_int_(A, B, C, rows_a, cols_a, cols_b) bind(C)
    USE :: ISO_FORTRAN_ENV
    USE :: ISO_C_BINDING
    IMPLICIT NONE

    INTEGER(KIND=C_INT), INTENT(IN) :: rows_a, cols_a, cols_b
    INTEGER(KIND=C_INT), DIMENSION(rows_a, cols_a), INTENT(IN) :: A
    INTEGER(KIND=C_INT), DIMENSION(cols_a, cols_b), INTENT(IN) :: B
    INTEGER(KIND=C_INT), DIMENSION(rows_a, cols_b), INTENT(OUT) :: C

    INTEGER :: i, j, k

    ! Perform matrix multiplication flipping indexing to keep standard with
    ! C/C++ calls
    DO i = 1, rows_a
        DO j = 1, cols_b

            C(j, i) = 0
            DO k = 1, cols_a

                C(j, i) = C(j, i) + A(k, i)*B(j, k)

            END DO

        END DO
    END DO

END SUBROUTINE mtx_mult_routine_int_

