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
!> FORTRAN subroutine testing the Matrix Addition subroutine
subroutine test_mtx_add()
    IMPLICIT NONE

    !< declare variables
    integer(kind=8) :: nrows, ncols
    real(kind=8), allocatable :: a(:, :), b(:, :), c(:, :)
    integer(kind=8) :: i, j
    logical :: failed

    !< initialize variables (e.g., set nrows and ncols)
    nrows = 3
    ncols = 3

    !< allocate memory for arrays
    allocate (a(nrows, ncols))
    allocate (b(nrows, ncols))
    allocate (c(nrows, ncols))

    !< initialize input arrays (a and b) with test data
    a = 1.0
    b = 2.0

    !< call the subroutine being tested (float version)
    call mtx_add_routine_float(a, b, c, nrows, ncols)

    !< check the output (c) against expected results
    failed = .false.
    do i = 1, nrows
        do j = 1, ncols
            if (c(i, j) /= a(i, j) + b(i, j)) then
                print *, ''//achar(27)//'[34m [!] LINALG MTX ADD (FLOAT) FAILED'//achar(27)//'[0m'
                failed = .true.
                exit
            end if
        end do
    end do

    !< call the subroutine being tested (int version)
    call mtx_add_routine_int(a, b, c, nrows, ncols)

    !< check the output (c) against expected results
    do i = 1, nrows
        do j = 1, ncols
            if (c(i, j) /= a(i, j) + b(i, j)) then
                print *, ''//achar(27)//'[34m [!] LINALG MTX ADD (INT) FAILED'//achar(27)//'[0m'
                failed = .true.
                exit
            end if
        end do
    end do

    !< free allocated memory for a,b,c
    deallocate (a, b, c)

    !< IF EXECUTION REACHES HERE, PASS!
    if (.not. failed) then
        print *, achar(27)//'[32m[LINALG MTX ADD PASSED]'//achar(27)//'[0m'
    end if
end subroutine test_mtx_add

!> FORTRAN Linear Alebra subroutine test driver
program main
    implicit none
    call test_mtx_add()
end program main

