subroutine matrix_addition(a, b, c, nrows, ncols)
  implicit none
  integer, intent(in) :: nrows, ncols
  real, intent(in) :: a(nrows, ncols), b(nrows, ncols)
  real, intent(out) :: c(nrows, ncols)
  integer :: i, j

  do i = 1, nrows
    do j = 1, ncols
      c(i, j) = a(i, j) + b(i, j)
    end do
  end do

end subroutine matrix_addition

