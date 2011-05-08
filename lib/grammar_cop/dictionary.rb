require "grammar_cop/link_grammar"

module GrammarCop
  class Dictionary
    extend LinkGrammar
    #call before create
    def self.set_dictionary_path(dir)
      dictionary_path_set(dir)
    end
    
    def self.create(language)
      create_dictionary(language)
    end
    
    def self.destroy(dict)
      delete_dictionary(dict)
    end
  end
end