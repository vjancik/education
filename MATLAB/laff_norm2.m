function [ alpha ] = laff_norm2( x )
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here

if ~isvector( x )
    alpha = 'FAILED';
    return
end

alpha = sqrt( laff_dot( x,x ) );


return
end