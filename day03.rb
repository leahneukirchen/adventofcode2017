require 'pp'

d = 368078

N = 20
a = Array.new(N) { Array.new(N, 0) }

x = y = N/2
a[x][y] = 1

y += 1

2.step(10, 2) { |n|
  steps = Array.new(n-1, [-1, 0]) +
          Array.new(n,   [ 0,-1]) +
          Array.new(n,   [ 1, 0]) +
          Array.new(n+1, [ 0, 1])
  steps.each { |(dx,dy)|
    a[x][y] = a[x-1][y-1] + a[x-1][y] + a[x-1][y+1] + 
              a[x  ][y-1] +             a[x  ][y+1] + 
              a[x+1][y-1] + a[x+1][y] + a[x+1][y+1]
    if a[x][y] > d
      p a[x][y]
      exit
    end
    x += dx
    y += dy
  }
}

a.each { |l| p l }
