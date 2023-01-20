module openMTPK 
    using CxxWrap
    @wrapmodule("../")

  function __init__()
    @initcxx
  end
end

using .openMTPK
