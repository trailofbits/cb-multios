require 'csv'

Message = Struct.new(:id, :name, :len, :type)

messages = CSV.read(File.expand_path("../messages.csv", __FILE__))[1..-1].map do |m|
  Message.new *m
end

File.open(File.expand_path("../../src/messages.h", __FILE__), 'w') do |f|
  f.puts '#pragma once'
  f.puts '#include "protocol.h"'
  f.puts "// Generated at #{Time.now}"

  messages.each do |m|
    f.puts
    f.puts "\#define #{m.name.upcase}_ID #{m.id}"
    f.puts "\#define #{m.name.upcase}_EXPECTED_LENGTH #{m.len}"
    f.puts "void* extract_#{m.name.downcase}(protocol_frame* frame);"
  end
end

File.open(File.expand_path("../../src/messages.c", __FILE__), 'w') do |f|
  f.puts "// Generated at #{Time.now}"
  f.puts DATA.read

  messages.each do |m|
    next if m.len == '0'
    f.puts
    f.puts <<-EOF
void* extract_#{m.name.downcase}(protocol_frame* frame) {
  if (frame->type != #{m.id}) _terminate(-1);
    EOF

    if m.len != '-1'
      f.puts <<-EOF
  if (frame->length != #{m.len}) _terminate(-1);
      EOF
    end

    f.puts <<-EOF
  return frame->value;
}
    EOF
  end
end

__END__
#include "protocol.h"
#include "messages.h"
