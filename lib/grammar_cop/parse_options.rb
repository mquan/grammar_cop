require 'grammar_cop/link_grammar'

module GrammarCop
  class ParseOptions
    extend LinkGrammar
    def self.create
      create_parse_options()
    end

    def self.destroy(opts)
      delete_parse_options(opts)
    end

    def self.set_linkage_limit(opts, limit)
      #some reason functions start w/ set/get result in SystemStackError
      linkage_limit_set(opts, limit) 
    end
    
    def self.get_linkage_limit(opts)
      linkage_limit_get(opts)
    end
    
    def self.set_short_length(opts, length)
      short_length_set(opts, length)
    end
    
    def self.get_short_length(opts)
      short_length_get(opts)
    end

  end
end