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
! linsys.f90

subroutine solveLinearSystem(A, b, x, n)
    implicit none
    integer, intent(in) :: n
    real, dimension(n, n), intent(inout) :: A
    real, dimension(n), intent(inout) :: b
    real, dimension(n), intent(out) :: x
    real :: factor
    integer :: i, j, k

    ! Forward elimination
    do k = 1, n - 1
        do i = k + 1, n
            factor = A(i, k)/A(k, k)
            A(i, k + 1:n) = A(i, k + 1:n) - factor*A(k, k + 1:n)
            b(i) = b(i) - factor*b(k)
        end do
    end do

    ! Back substitution
    x(n) = b(n)/A(n, n)
    do i = n - 1, 1, -1
        x(i) = (b(i) - dot_product(A(i, i + 1:n), x(i + 1:n)))/A(i, i)
    end do

end subroutine solveLinearSystem

program main
    implicit none
    integer, parameter :: n = 3
    real :: A(n, n), b(n), x(n)
    integer :: i

    ! Initialize matrix A and vector b
    A = reshape([1.0, 2.0, -1.0, 3.0, 1.0, 1.0, 2.0, -1.0, 2.0], [n, n])
    b = [3.0, 4.0, 5.0]

    ! Solve the linear system
    call solveLinearSystem(A, b, x, n)

    ! Output the solution
    write (*, *) "Solution:"
    do i = 1, n
        write (*, *) "x(", i, ") = ", x(i)
    end do

end program main

