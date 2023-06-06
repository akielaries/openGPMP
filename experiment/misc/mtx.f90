program matrix_addition
    implicit none

    integer, parameter :: matrixSize = 1000
    integer :: i, j
    integer, dimension(matrixSize, matrixSize) :: A, B, C

    ! Initialize random number generator
    call random_seed()

    ! Populate matrices A and B with random values
    call random_fill(A)
    call random_fill(B)

    ! Perform matrix addition
    call matrixAddition(A, B, C)

    ! Display the matrices
    print *, "Matrix A:"
    do i = 1, matrixSize
        do j = 1, matrixSize
            print *, A(i, j)
        end do
    end do

    print *, "Matrix B:"
    do i = 1, matrixSize
        do j = 1, matrixSize
            print *, B(i, j)
        end do
    end do

    print *, "Matrix C after addition:"
    do i = 1, matrixSize
        do j = 1, matrixSize
            print *, C(i, j)
        end do
    end do

contains

    subroutine random_fill(matrix)
        integer, dimension(:, :), intent(inout) :: matrix
        integer :: i, j

        do i = 1, size(matrix, 1)
            do j = 1, size(matrix, 2)
                matrix(i, j) = int(random_number() * 100)
            end do
        end do
    end subroutine random_fill

    subroutine matrixAddition(A, B, C)
        integer, dimension(matrixSize, matrixSize), intent(in) :: A, B
        integer, dimension(matrixSize, matrixSize), intent(out) :: C
        integer :: i, j

        do i = 1, matrixSize
            do j = 1, matrixSize
                C(i, j) = A(i, j) + B(i, j)
            end do
        end do
    end subroutine matrixAddition

end program matrix_addition

