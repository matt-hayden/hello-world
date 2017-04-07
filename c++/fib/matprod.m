
function mr = matprod(m3d)
  mr = m3d(:,:,1);
  [_, _, z] = size(m3d);
  for d = 2:z
    mr *= m3d(:,:,d);
  endfor
endfunction
