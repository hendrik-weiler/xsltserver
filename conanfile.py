from conans import ConanFile, CMake

class MyProjectConan(ConanFile):
    settings = ('os', 'compiler', 'build_type', 'arch')
    requires = (
        'civetweb/1.14',
        'libxslt/1.1.34',
    )
    generators = 'cmake'
    default_options = {}

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def imports(self):
        self.copy('*.dll', src='bin', dst='bin')
        self.copy('*.dylib*', src='lib', dst='lib')
        self.copy('*.so', src='lib', dst='lib')
