require 'test/unit'
require_relative 'fib-sequence'

class FibonacciSequenceTest < Test::Unit::TestCase
  def setup
    @test_obj = FibonacciSequence.new
  end
  
  # do testu budou zahrnuty metody s prefixem "test_", tj. napr. nasledujici
  def test_method
    assert_equal( true, true )
  end
  
  def test_initialize
    assert_equal( @test_obj.instance_variable_get(:@seq), [0,1])
    assert_equal( @test_obj.instance_variable_get(:@idx), -1)
  end

  def test_next
    retVal = @test_obj.next
    assert_equal( @test_obj.instance_variable_get(:@idx), 0)
    assert_equal( retVal, 0)
  end

  def test_indexing
    test_obj2 = FibonacciSequence.new

    for i in 0..99
      assert_equal(@test_obj.next,test_obj2[i])
    end
  end

  def test_current
    retVal = @test_obj[5]
    assert_equal( retVal, 5 )
  end

  def test_reset
    @test_obj[8]
    @test_obj.reset
    assert_equal(@test_obj.instance_variable_get(:@idx), -1)
  end

  def test_current_idx
    @test_obj[10]
    assert_equal(@test_obj.current_idx, 10)
  end

  def test_nil
    assert_equal(@test_obj.current, nil)
    assert_equal(@test_obj.current_idx, nil)
    assert_equal(@test_obj[-8], nil)
  end
end
