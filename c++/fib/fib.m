
function retval = fib(n)
  if (n < 1)
    retval = 0;
    return;
  endif
  persistent fib_2n;
  if (isempty(fib_2n))
    fib_2n = matmulexp([1 1; 1 0], 2, 11);
  endif
  b = bitget(uint64(n), 1:64);
  mr = matprod(fib_2n(:,:,b));
  retval = mr(1,2);
endfunction
