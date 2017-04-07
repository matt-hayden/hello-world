
function retval = fib(n)
  if (n < 1)
    retval = 0;
    return;
  endif
  persistent fib_2n;
  if (isempty(fib_2n))
    t = fib_2n(:,:,1) = [ 1 1 ; 1 0 ];
    for i = 2:11
      fib_2n(:,:,i) = t = t**2;
    endfor
  endif
  b = bitget(uint64(n), 1:64);
  mr = matprod(fib_2n(:,:,b));
  retval = mr(1,2);
endfunction
