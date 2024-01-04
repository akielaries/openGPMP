import example

x = example.X()

# Testing overloaded functions
print(x.f(10))                            # Should call bool f(int a)
print(x.f(10, 3.14))                      # Should call bool f(int a, double b)
print(x.f(10, 3.14, 'c'))                 # Should call bool f(int a, double b, char c)
print(x.f(1, 2, 3))                       # Should call int f(int a, int b, int c)

