class Equation 
  def self.solve_quadratic(a, b, c)
    if a==0 and b==0
      return nil
    end
    if a==0
      return [-c/b.to_f]
    end
    if (b**2 - 4*a*c) > 0
      disc = Math.sqrt(b**2 - 4*a*c)
      return [(-b+disc)/(2*a).to_f,(-b-disc)/(2*a).to_f]
    elsif (b**2 - 4*a*c) == 0
      return [(-b / (2*a))]
    else
      return nil
    end
  end
end
