function [ x_out ] = laff_scal( alpha, x )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

[ m_x, n_x ] = size( x );

if ~isscalar( alpha )
    x_out = 'FAILED';
    return
end

if ~isvector( x )
    x_out = 'FAILED';
    return
end

if ( n_x == 1)
    for i=1:m_x
        x( i,1 ) = alpha * x( i,1 );
    end
else
    for i=1:n_x
        x( 1,i ) = alpha * x( 1,i );
    end
end

x_out = x;

return
end

