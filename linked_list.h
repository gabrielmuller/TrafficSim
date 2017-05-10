// Copyright [2017] <Gabriel M�ller>

#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>
#include <string>
#include <sstream>

namespace structures {

template <typename T>

/**
 * Implementa��o de lista encadeada.
 */
class LinkedList {
 public:
  /** N�o h� declara��o de construtor.
   *  Os atributos j� s�o iniciados com os valores corretos.
   */

  /** Destrutor.
   *  Chama o m�todo 'clear' para limpar a lista.
   */
  ~LinkedList() { clear(); }

  /** Limpa a lista.
   *  Deleta todos elementos da mem�ria e reinicia os atributos.
   */
  void clear() {
    if (!empty()) {
      Node* prev = head;
      Node* next;
      for (int i = 0; i < size(); i++) {
        next = prev->next();
        delete prev;
        prev = next;
      }
      size_ = 0;
      head = nullptr;
    }
  }

  /** Adiciona elemento ao fim da lista.
   *  \param data dado a ser adicionado.
   */
  void push_back(const T& data) { insert(data, size()); }

  /** Adiciona elemento ao come�o da lista.
   *  \param data dado a ser adicionado.
   */
  void push_front(const T& data) {
    Node* node = new Node(data);
    if (node == nullptr) {
      throw std::out_of_range("Lista cheia");
    }
    if (!empty()) {
      node->next(head);
    }
    head = node;
    size_++;
  }

  /** Insere elemento na posi��o especificada.
   *  \param data dado a ser adicionado.
   *  \param index posi��o a adicionar.
   */
  void insert(const T& data, std::size_t index) {
    if (index > size_) {
      throw std::out_of_range("Posi��o n�o existe");
    }
    if (index == 0) {
      push_front(data);
    } else {
      Node* node = new Node(data);
      if (node == nullptr) {
        throw std::out_of_range("Lista cheia");
      }
      Node* it = head;
      for (int i = 0; i < index - 1; i++) {
        it = it->next();
      }
      node->next(it->next());
      it->next(node);
      size_++;
    }
  }

  /** Insere o dado seguindo o ordenamento do tipo do dado.
   *  \param data dado a ser adicionado.
   */
  void insert_sorted(const T& data) {
    Node* it = head;
    int i;
    for (i = 0; i < size(); i++) {
      if (data < it->data()) {
        insert(data, i);
        break;
      }
      it = it->next();
    }
    if (i == size()) {
      push_back(data);
    }
  }

  /** Dado na posi��o especificada.
   *  \param index posi��o.
   *  \return dado por refer�ncia.
   */
  T& at(std::size_t index) {
    if (index >= size_) {
      throw std::out_of_range("Posi��o n�o existe");
    }
    int i = 0;
    Node* it = head;

    while (i < index) {
      it = it->next();
      i++;
    }
    return it->data();
  }

  /** Remove e retorna dado da posi��o especificada.
   *  \param index posi��o.
   *  \return dado.
   */
  T pop(std::size_t index) {
    if (index >= size()) {
      throw std::out_of_range("Posi��o n�o existe");
    }

    if (index == 0) {
      return pop_front();
    }

    Node* it = head;
    for (int i = 1; i < index; i++) {
      it = it->next();
    }
    size_--;

    Node* toPop = it->next();
    T output = toPop->data();
    it->next(toPop->next());
    delete toPop;
    return output;
  }

  /** Remove e retorna dado de tr�s.
   *  \return dado.
   */
  T pop_back() { return pop(size() - 1); }

  /** Remove e retorna dado da frente.
   *  \return dado.
   */
  T pop_front() {
    if (empty()) {
      throw std::out_of_range("Lista vazia");
    }
    size_--;
    T output = head->data();
    Node* next = head->next();
    delete head;
    head = next;

    return output;
  }

  /** Remove o dado especificado
   *  \param data dado por refer�ncia.
   */
  void remove(const T& data) { pop(find(data)); }

  /** Lista vazia?
   *  \return true se vazia.
   */
  bool empty() const { return size_ == 0; }

  /** Cont�m o dado?
   *  \param data dado por refer�ncia.
   *  \return true se o dado estiver contido.
   */
  bool contains(const T& data) const { return find(data) != size_; }

  /** Posi��o do dado especificado.
   *  \param data dado por refer�ncia.
   *  \return posi��o do dado.
   */
  std::size_t find(const T& data) const {
    if (empty()) {
      throw std::out_of_range("Lista vazia");
    }
    Node* it = head;
    int i;
    for (i = 0; i < size() && it->data() != data; i++) {
      it = it->next();
    }
    return i;
  }

  /** Tamanho.
   *  \return n�mero de elementos da lista.
   */
  std::size_t size() const { return size_; }

  /** Lista para string.
   * \return string com todos elementos da lista, com quebra de linha.
   */
  std::string to_string() {
	  Node* it = head;
	  std::ostringstream output;
	  for (int i = 0; i < size_; i++) {
		  output << it->data().to_string() << std::endl;
		  it = it->next();
	  }
	  return output.str();
  }

 private:
  /** Elemento de lista.
   *
   */
  class Node {  // Elemento
   public:
    /** Construtor por dado.
     *  \param data dado por refer�ncia.
     */
    explicit Node(const T& data) : data_{data} {}

    /** Construtor por dado e pr�ximo elemento.
     *  \param data dado por refer�ncia.
     *  \param next pr�ximo elemento no contexto da lista.
     */
    Node(const T& data, Node* next) : data_{data}, next_{next} {}

    /** Dado.
     *  \return dado por refer�ncia.
     */
    T& data() {  // getter: dado
      return data_;
    }

    /** Dado para leitura.
     *  \return dado por refer�ncia.
     */
    const T& data() const {  // getter const: dado
      return data_;
    }

    /** Pr�ximo elemento.
     *  \return pr�ximo elemento.
     */
    Node* next() {  // getter: pr�ximo
      return next_;
    }

    /** Pr�ximo elemento para leitura.
     *  \return pr�ximo elemento.
     */
    const Node* next() const {  // getter const: pr�ximo
      return next_;
    }

    /** Definir pr�ximo elemento.
     *  \param node pr�ximo elemento.
     */
    void next(Node* node) {  // setter: pr�ximo
      next_ = node;
    }
   private:
    T data_;              /**< Dado do elemento. */
    Node* next_{nullptr}; /**< Pr�ximo elemento. */
  };

  /** �ltimo elemento da lista.
   *  \return �ltimo elemento.
   */
  Node* end() {  // �ltimo nodo da lista
    auto it = head;
    for (auto i = 1u; i < size(); ++i) {
      it = it->next();
    }
    return it;
  }

  Node* head{nullptr};   /**< Primeiro elemento da lista ("cabe�a"). */
  std::size_t size_{0u}; /**< Tamanho da lista. */
};
}  // namespace structures

#endif
