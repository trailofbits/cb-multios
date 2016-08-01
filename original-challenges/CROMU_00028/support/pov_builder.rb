require 'nokogiri'

SAFE_CELL_COUNT = 4096 * 2**3
PARTY_CELLS = (SAFE_CELL_COUNT...(2 * SAFE_CELL_COUNT))

include Nokogiri::XML

xml = Document.parse DATA.read
target = xml.css('replay').first

write_type_len = [32, 2].pack('C2')

PARTY_CELLS.each do |c|
  enc = [c].pack('S<')
  w = Node.new 'write', xml
  w << Node.new('data', xml).tap do |d| 
    bs = [write_type_len, enc].join('').bytes
    fmt = ("\\x%02x" * 4) % bs
    d.children = fmt
  end
  target << w
  target << "\n"
  r = Node.new('read', xml)
  r << Node.new('length', xml).tap do |l|
    l.children = '2'
  end
  target << r
  target << "\n"
end

File.open(File.expand_path("../../pov/pov-gen.xml", __FILE__), 'w') do |f|
  xml.write_to f
end

__END__
<?xml version="1.0" standalone="no" ?>
<!DOCTYPE pov SYSTEM "/usr/share/cgc-docs/replay.dtd">
<pov>
<cbid>service</cbid>
<replay>
    <!-- hello -->
    <read><length>2</length><match><data>\x00\x00</data></match></read>
    <write><data>\x00\x00</data></write>
    <!-- using evils \x5b243\x2c 0\x2c 60\x2c 0\x2c 25\x2c 0\x2c 155\x2c 0\x5d -->
    <write><data>\x01\x02\xf3\x00</data></write>
    <read><length>2</length><match><data>\x02\x00</data></match></read>
    <write><data>\x01\x02\x00\x00</data></write>
    <read><length>2</length><match><data>\x02\x00</data></match></read>
    <write><data>\x01\x02\x3c\x00</data></write>
    <read><length>2</length><match><data>\x02\x00</data></match></read>
    <write><data>\x01\x02\x00\x00</data></write>
    <read><length>2</length><match><data>\x02\x00</data></match></read>
    <write><data>\x01\x02\x19\x00</data></write>
    <read><length>2</length><match><data>\x02\x00</data></match></read>
    <write><data>\x01\x02\x00\x00</data></write>
    <read><length>2</length><match><data>\x02\x00</data></match></read>
    <write><data>\x01\x02\x9b\x00</data></write>
    <read><length>2</length><match><data>\x02\x00</data></match></read>
    <write><data>\x01\x02\x00\x00</data></write>
    <read><length>2</length><match><data>\x02\x00</data></match></read>
    <!-- at menu -->

</replay>
</pov>
