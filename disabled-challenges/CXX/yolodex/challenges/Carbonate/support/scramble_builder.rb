phase_count = 8;

File.open(File.expand_path("../../src/scramble_gen.h", __FILE__), 'w') do |f|
  f.puts "// Generated at #{Time.now}"
  f.puts '#pragma once'
  f.puts '#include "scramble.h"'

  f.puts
  f.puts "#define PHASE_COUNT #{phase_count}"
  f.puts

  phase_count.times do |phase|
    f.puts "scramble_item phase_#{phase}(scramble_item i, scramble_item j);"
  end
end

File.open(File.expand_path("../../src/scramble_gen.c", __FILE__), 'w') do |f|
  f.puts "// Generated at #{Time.now}"
  f.puts '#include <libcgc.h>'
  f.puts '#include "scramble_gen.h"'
  f.puts

  phase_count.times do |phase|
    f.puts "scramble_item phase_#{phase}(scramble_item i, scramble_item j) {"
    10.times do
      4.times do
        shift_point = rand(12) + 2
        shift_dir = %w{<< >>}.shuffle.first
        rando = if (rand() > 0.5)
                  op = %w{& ^ |}.shuffle.first
                  " #{op} 0x#{rand(2**14).to_s(16)}"
                else
                  ''
                end
        
        f.puts "  i.i = i.i ^ (j.i #{shift_dir} #{shift_point})#{rando};"
        
        operation = %w{sin cos tan log2}.shuffle.first
        kajigger = rand() * 3.14 + 0.1
        
        f.puts "  j.f = #{operation}(i.f * j.f * #{kajigger});"
      end
    end
    f.puts "  return i;"
    f.puts "}"
    f.puts
  end
end
