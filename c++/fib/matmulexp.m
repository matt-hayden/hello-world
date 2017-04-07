
function mr = matmulexp(init, to_power, array_size)
  printf("Calling matmulexp(...)\n");
  t = mr(:,:,1) = init;
  for i = 2:array_size
    t = mr(:,:,i) = t**to_power;
  endfor
endfunction
