
def sum(array)
  if array.empty?
    return 0
  end
  return array.sum
end

def max_2_sum(array)
  if array.empty?
    return 0
  elsif array.length == 1
    return array[0]
  else
    array.delete_at(array.find_index(max = array.max))
    max2 = array.find_index(array.max)
    return max+max2
  end
end

def sum_to_n?(array,n)
  if array.empty? || array.length == 1
    return false
  else
    for i in 0..array.length
      for j in i+1..array.length
        if array[i]+array[j]==n
          return true
        end
      end
    end
  end
end
