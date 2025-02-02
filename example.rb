require_relative 'ractorwrap'

internal_ary = [+"a", +"b", +"c"]
p Ractor.shareable? internal_ary # => false
ary = RactorWrap.new.wrap(internal_ary)
p Ractor.shareable? ary #=> true

r1 = Ractor.new(ary) do |ary|
  loop do |i|
    ary.push(i)
  end
end
r2 = Ractor.new(ary) do |ary|
  loop do
    p ary.length
  end
end
r1.take
r2.take
