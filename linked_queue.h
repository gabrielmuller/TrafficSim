// Copyright 2017 Juliana Silva Pinheiro

#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

/**
 * @brief Classe implementa uma estrutura de dados do tipo Fila Encadeada, 
 *          onde o primeiro elemento a ser inserido é o primeiro a ser retirado
 *          (Fist In First Out/FIFO), de modo dinâmico.
 *
 * @tparam  T   Parâmetro genérico de Template
 */
template<typename T>
class LinkedQueue {
 public:
    /**
     * @brief       Construtor padrão
     */
    LinkedQueue() = default;

    ~LinkedQueue();

    void clear();

    void enqueue(const T& data);

    T dequeue();

    T& front() const;

    T& back() const;

    bool empty() const;

    std::size_t size() const;

 private:
/**
  * @brief  Classe elemento da fila encadeada, com um dado e um ponteiro para o
  *         próximo elemento da fila.
  */
    class Node {
     public:
        /**
         * @brief   Construtor da classe Node definindo data_, com next_ padrão 
         *          (nullptr)
         */
        explicit Node(const T& data):
            data_{data}
        {}

        /**
         * @brief   Construtor da classe Node
         */
        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        /**
         * @brief   Método retorna data_ por referência 
         */
        T& data() {
            return data_;
        }

        /**
         * @brief   Método retorna constante data_ por referência
         */
        const T& data() const {
            return data_;
        }

        /**
         * @brief   Método retorna next_
         */
        Node* next() {
            return next_;
        }

        /**
         * @brief   Método retorna constante next_ 
         */
        const Node* next() const {
            return next_;
        }

        /**
         * @brief   Método define o atributo next_
         */
        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;  /* Dado do elemento */
        Node* next_{nullptr};  /* Ponteiro para o elemento seguinte */
    };

    /**
      * @brief   Método retorna o último elemento Node da fila 
      */
    Node* end() {
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};  /* Node-cabeça */
    Node* tail{nullptr};  /* Último node */
    std::size_t size_{0u};  /* Tamanho da fila */
};

/**
 * @brief       Destrutor da classe Fila
 *
 * @tparam      T    Parâmetro genérico de Template
 *
 */
template<typename T>
LinkedQueue<T>::~LinkedQueue() {
    clear();
}

/**
 * @brief       Retira todos os elementos da fila, retornando ao estado inicial
 *
 * @tparam      T    Parâmetro genérico de Template
 *
 */
template<typename T>
void LinkedQueue<T>::clear() {
    while (!empty())
        dequeue();
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

/**
 * @brief       Insere um novo elemento no final da Fila.
 *
 * @param[in]   data    Elemento a ser inserido
 *
 * @tparam      T       Parâmetro genérico de Template
 *
 */
template<typename T>
void LinkedQueue<T>::enqueue(const T& data) {
    Node *added = new Node(data);
    if (added == nullptr)
        throw std::out_of_range("Full queue");
    if (empty()) {
        head = added;
        tail = head;
    } else {
        tail->next(added);
        tail = tail->next();
    }
    ++size_;
}

/**
 * @brief       Retira o elemento no início da fila e o retorna.
 *              Exceção std::out_of_range caso a fila esteja vazia.
 *
 * @tparam      T    Parâmetro genérico de Template
 *
 * @return      Elemento retirado do início da fila.
 *
 */
template<typename T>
T LinkedQueue<T>::dequeue() {
    if (empty())
        throw std::out_of_range("Empty queue");
    T back = head->data();
    head = head->next();
    if (size_ == 1)
        tail = nullptr;
    --size_;
    return back;
}

/**
 * @brief       Retorna o dado do Node no início da fila (sem retirá-lo).
 *              Exceção std::out_of_range caso a fila esteja vazia.
 *
 * @tparam      T    Parâmetro genérico de Template
 *
 * @return      Elemento no início da fila.
 *
 */
template<typename T>
T& LinkedQueue<T>::front() const {
    if (empty())
        throw std::out_of_range("Empty queue");
    return head->data();
}

/**
 * @brief       Retorna o dado do Node no final da fila (sem retirá-lo).
 *              Exceção std::out_of_range caso a fila esteja vazia.
 *
 * @tparam      T    Parâmetro genérico de Template
 *
 * @return      Elemento no final da fila.
 *
 */
template<typename T>
T& LinkedQueue<T>::back() const {
    if (empty())
        throw std::out_of_range("Empty queue");
    return tail->data();
}

/**
 * @brief       Checa se a fila está vazia.
 *
 * @tparam      T    Parâmetro genérico de Template
 *
 * @return      True se a fila estiver vazia, caso contrário retorna False.
 *
 */
template<typename T>
bool LinkedQueue<T>::empty() const {
    return size_ == 0;
}

/**
 * @brief       Retorna a quantidade de elementos na fila.
 *
 * @tparam      T    Parâmetro genérico de Template
 *
 * @return      Quantidade de elementos na fila
 *
 */
template<typename T>
std::size_t LinkedQueue<T>::size() const {
    return size_;
}

}  // namespace structures

#endif
