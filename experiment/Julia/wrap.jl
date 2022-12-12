module RM_pkg
    using CxxWrap
    @wrapmodule("../")

  function __init__()
    @initcxx
  end
end

using .RM_pkg

