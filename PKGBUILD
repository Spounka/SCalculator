# Maintainer: Nazih Boudaakkar <nazih@boudaakkarnazih.tk>

pkgname=scalculator
pkgver=1.0
pkgrel=1
pkgdesc="A lightweight fast calculator written in gtkmm"
arch=('x86_64')
url="https://github.com/Spounka/SCalculator/"
license=('MIT')
depends=('gtkmm3')
makedepends=('cmake')
source=("git+https://github.com/Spounka/SCalculator.git")
sha256sums=('SKIP')
provides=('scalculator')

build(){
    cmake -B $srcdir/build/release -DCMAKE_BUILD_TYPE=Release -Wno-dev -S $srcdir/SCalculator/
    cd $srcdir/build/release

    make -j -C $srcdir/build/release
}
package() {
    install -d "${pkgdir}/usr/share/${pkgname}/ui/"
    install -d "${pkgdir}/usr/lib"
    install -d "${pkgdir}/usr/bin"

    install -v "${srcdir}/SCalculator/${pkgname}/ui/calculator.glade" "${pkgdir}/usr/share/${pkgname}/ui/"
    install -vD "${srcdir}/build/release/bin/$pkgname" "$pkgdir/usr/bin/$pkgname"
    install -vD "${srcdir}/build/release/lib/libSCalculator.so" "$pkgdir/usr/lib/libSCalculator.so"
}
