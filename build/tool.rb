require "#{ENV['CORTO_BUILD']}/common"

if not defined? TARGET then
    raise "library: TARGET not specified\n"
end

TARGETDIR = "#{ENV['CORTO_TARGET']}/bin"
ARTEFACT = "#{TARGET}"
INCLUDE << "include"

# Bootstrap: Explicitly add corto library. The buildsystem invokes the corto
# tool to find packages, however, this rakefile is used to build the corto tool.
# USE_PACKAGE << "corto"
LINK << "#{CORTO_TARGET}/lib/corto/#{CORTO_VERSION}/corto/corto"

require "#{ENV['CORTO_BUILD']}/artefact"
