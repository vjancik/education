function [ y_out ] = laff_copy( x, y)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

[ m_x, n_x ] = size( x );
[ m_y, n_y ] = size( y );

if ( m_x ~= 1 && n_x ~= 1) || ( m_y ~= 1 && n_y ~= 1)
    y_out = 'FAILED';
    return
end

if (m_x * n_x ~= m_y * n_y)
    y_out = 'FAILED';
    return
end

if ( n_x == 1 )
    if ( n_y ==1 )
        for i=1:m_x
            y( i,1 ) = x( i,1 );
        end
    else
        for i=1:m_x
            y( 1,i ) = x( i,1 );
        end
    end
else
    if ( n_y == 1)
        for i=1:n_x
            y( i,1 ) = x( 1,i );
        end
    else
        for i=1:n_x
            y( 1,i ) = x( 1,i );
        end
    end
end

y_out = y;

return
end

