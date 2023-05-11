#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <boost/algorithm/string.hpp>
#include "edge.h"

class Parser {
	public:
        void parse(std::string file_path);
        void printGraph(std::string folder_path);

        private:
        // member vars

        std::unordered_map<std::string, Edge*> edges_; // startid +endid
        std::unordered_map<std::string, Node*> nodes_; // lang+term : node_obj
        const std::map<std::string, relType> typeMap_ = {
            {"inherited_from", inherited_from},
            {"borrowed_from", borrowed_from},
            {"derived_from", derived_from},
            {"learned_borrowing_from", learned_borrowing_from},
            {"semi_learned_borrowing_from", semi_learned_borrowing_from},
            {"orthographic_borrowing_from", orthographic_borrowing_from},
            {"unadapted_borrowing_from", unadapted_borrowing_from},
            {"root", root},
            {"has_prefix", has_prefix},
            {"has_prefix_with_root", has_prefix_with_root},
            {"has_suffix", has_suffix},
            {"has_suffix_with_root", has_suffix_with_root},
            {"has_confix", has_confix},
            {"has_affix", has_affix},
            {"compound_of", compound_of},
            {"doublet_with", doublet_with},
            {"is_onomatopoeic", is_onomatopoeic},
            {"calque_of", calque_of},
            {"semantic_loan_of", semantic_loan_of},
            {"named_after", named_after},
            {"phono-semantic_matching_of", phono_semantic_matching_of},
            {"blend_of", blend_of},
            {"clipping_of", clipping_of},
            {"abbreviation_of", abbreviation_of},
            {"initialism_of", initialism_of},
            {"etymologically_related_to", etymologically_related_to},
            {"cognate_of", cognate_of},
            {"group_affix_root", group_affix_root},
            {"group_related_root", group_related_root},
            {"group_derived_root", group_derived_root},
            {"back-formation_from", back_formation_from}
        };
};