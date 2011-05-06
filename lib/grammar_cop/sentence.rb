require 'grammar_cop/link_grammar'

module GrammarCop
  class Sentence
    extend LinkGrammar
    def self.create(text, dictionary)
      create_sentence(text, dictionary)
    end

    def self.parse(sentence, options)
      parse_sentence(sentence, options)
    end
    
    def self.destroy(sentence)
      delete_sentence(sentence)
    end
  end
end