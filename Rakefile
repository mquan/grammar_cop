require 'bundler'
require "rake/extensiontask"

Rake::ExtensionTask.new("link_grammar") do |extension|
  extension.lib_dir = "lib/grammar_cop"
end

Bundler::GemHelper.install_tasks
