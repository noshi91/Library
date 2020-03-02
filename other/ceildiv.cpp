template <class T> T ceildiv(const T &n, const T &d) {
  return n / d + (n % d != 0 ? 1 : 0);
}
