require 'grammar_cop/link_grammar'

module GrammarCop
  class Linkage
    extend LinkGrammar
    def self.create(k, sentence, opts)
      create_linkage(k, sentence, opts)
    end

    def self.destroy(linkage)
      delete_linkage(linkage)
    end
    
    def self.create_diagram(linkage)
      print_linkage_diagram(linkage)
    end
    
    def self.sublinkages_count(linkage)
      linkage_count_sublinkages(linkage)
    end
    
    def self.num_words_count(linkage)
      linkage_count_num_words(linkage)
    end
    
    def self.num_links_count(linkage)
      linkage_count_num_links(linkage)
    end
  end
end