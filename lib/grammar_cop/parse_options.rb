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

    def self.set_disjunct_cost(opts, cost)
      disjunct_cost_set(opts, cost)
    end
    
    def self.get_disjunct_cost(opts)
      disjunct_cost_get(opts)
    end
    
    def self.set_min_null_count(opts, count)
      min_null_count_set(opts, count)
    end
    
    def self.get_min_null_count(opts)
      min_null_count_get(opts)
    end
    
    def self.set_max_null_count(opts, count)
      max_null_count_set(opts, count)
    end
    
    def self.get_max_null_count(opts)
      max_null_count_get(opts)
    end
    
    def self.set_null_block(opts, block)
      options_null_block_set(opts, block)
    end
    
    def self.get_null_block(opts)
      options_null_block_get(opts)
    end
    
    def self.set_islands_ok(opts, ok)
      options_null_block_set(opts, ok)
    end
    
    def self.get_islands_ok(opts)
      islands_ok_get(opts)
    end
  end
end