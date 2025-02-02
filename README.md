# ractorwrap-broken

## THIS IS A BROKEN PROTOTYPE

ractorwrap-broken is an attempt to create a wrapper allowing sharing non-shareable objects between Ractors. It is broken and does not work.

- No concurrency control takes place, so the internal object can be modified by multiple Ractors at the same time, resulting in unexpected behavior.

## Usage

```
gcc -I /path/to/include/ruby-3.5.0+0 -I /path/to/master/include/ruby-3.5.0+0/x86_64-linux -fPIC -shared -o wrapper.so wrapper.c
```

```ruby
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
```
