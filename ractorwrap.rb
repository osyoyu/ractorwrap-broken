# frozen_string_literal: true

require_relative 'wrapper'

class RactorWrap
  def wrap(obj)
    @ractor = Ractor.new do
      _obj = Ractor.receive
      loop do
        name, args, block = Ractor.receive
        Ractor.yield _obj.send(name, *args, &block)
      end
    end
    @ractor.send(obj, move: true)
    self.freeze
    self
  end

  def method_missing(name, *args, &block)
    # This is broken since no concurrency control is in action
    @ractor.send([name, args, block])
    @ractor.take
  end
end
