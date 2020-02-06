
GEN_POV_DIR = support/gen_pov
pov_gen:
	generate-polls --count 1 --depth 20 $(GEN_POV_DIR)/machine.py $(GEN_POV_DIR)/state-graph.yaml $(GEN_POV_DIR)
	cp $(GEN_POV_DIR)/*.xml pov/POV_00099.xml

pov_clean:
	rm -f $(GEN_POV_DIR)/*.xml $(GEN_POV_DIR)/*.png $(GEN_POV_DIR)/*.dot

