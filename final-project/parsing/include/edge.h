#pragma once
#include <string>
#include "node.h"
#include <list>
//#include "../../utf8proc-2.6.1/utf8proc.h"

enum relType {
	inherited_from,
	borrowed_from,
	derived_from,
	learned_borrowing_from,
	semi_learned_borrowing_from,
	orthographic_borrowing_from,
	unadapted_borrowing_from,
	root,
	has_prefix,
	has_prefix_with_root,
	has_suffix,
	has_suffix_with_root,
	has_confix,
	has_affix,
	compound_of,
	doublet_with,
	is_onomatopoeic,
	calque_of,
	semantic_loan_of,
	named_after,
	phono_semantic_matching_of, //phono-semantic_matching_of in csv
	blend_of,
	clipping_of,
	abbreviation_of,
	initialism_of,
	
	etymologically_related_to,
	cognate_of,
	group_affix_root,
	group_related_root,
	group_derived_root,
	back_formation_from
}; 

class Edge {
	public:
		Edge(Node* start, Node* end, std::string relation);
		Node* getStart() const;
		Node* getEnd() const;
		std::list<std::string> getRelTypes() const;
		void addRelType(std::string relType);

	private:
		//unsigned start;
		//unsigned end;
		Node * start_;
		Node * end_;
		std::list<std::string> relations_;
};