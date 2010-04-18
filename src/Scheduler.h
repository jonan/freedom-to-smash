/**
File: Scheduler.h
*/

#pragma once


#include <set>
#include <stdexcept>
#include "ITask.h"
#include "ScheduledItem.h"


	//!
	//! Clase Scheduler (Programador). Permite planificar Tareas, que serán ejecutadas
	//! al pasar determinado tiempo. El tiempo de la clase es relativo. La clase está
	//! optimizada para la ejecución e inserción de tareas. 
	//!
	class Scheduler
	{
		unsigned long lastID;

		unsigned long mCurrentTime;
		std::set< ScheduledItem::Ptr, ScheduledItem::LessThanFunctor> mSet;

		//! Función privada.
		//! Genera una nueva ID de Tarea. Las IDs deben ser únicas dentro del
		//! mismo Scheduler. Entre otras cosas, sirven para diferenciar a los
		//! objetos ScheduledItem que tienen el mismo tiempo de ejecución y
		//! la misma prioridad, permitiéndo ordenarlos estrictamente.
		unsigned long GenerateNewID();

		//! Función privada.
		//! Ejecuta las Tareas que debe. Llamado por Update().
		void RunDueTasks();

	public:

		typedef int TaskID;


		class Exception : public std::runtime_error
		{
		public:
			Exception(std::string const & msg) : std::runtime_error(msg) { }
		};


		//! Inicializa el Scheduler, opcionalmente con un tiempo concreto.
		//!
		//! @param curtime Tiempo actual. Es relativo así que puede ser dado 
		//! en cualquier unidad.
		Scheduler(unsigned long curtime = 0);

		//! Asigna un valor al tiempo interno.
		//!
		void SetInternalTime(unsigned long curtime);


		//! Añade una nueva tarea al Scheduler. Las tareas deben heredar de ITask.
		//! La primera ejecución tendrá lugar después de que pase el número de unidades
		//! de tiempo especificadas por el parámetro wait. 
		//!
		//! @param task Puntero a la Tarea a ejecutar.
		//!
		//! @param wait Tiempo a esperar antes de ejecutar la Tarea por primera vez.
		//!
		//! @param times Número de veces a ejecutar la Tarea, esperando inicialmente
		//! según wait y tras cada vez adicional, según frequency.
		//!
		//! @param frequency Tiempo a esperar tras cada ejecución para la siguiente.
		//! Si toma el valor ITask::FREQ_ASWAIT se considera que la frecuencia es la
		//! de wait.
		//!
		//! @param priority La prioridad puede ser PRIORITY_LOW, PRIORITY_NORMAL, 
		//! PRIORITY_HIGH, o cualquier número, siendo las prioridades negativas las más 
		//!	bajas. 
		//!
		//! @return Un TaskID identificando la Tarea.
		//!
		//! @remark Una tarea no se ejecuta nunca más de una vez por ciclo (Update).
		//! En caso de que el delta exceda la frecuencia, la Tarea se ejecutará
		//! al siguiente ciclo, o a los siguientes, hasta llegar al número de veces
		//! apropiado.
		TaskID AddTask(ITask::Ptr const & task, unsigned long wait, long times = 1,
			long frequency = ITask::FREQ_ASWAIT, int priority = ITask::PRIORITY_NORMAL );


		//! Quita una Tarea del Scheduler, utilizando el identificador de Tarea 
		//! (TaskID).
		//! @param taskID El TaskID devuelto al añadir la Tarea.
		void RemoveTask(TaskID taskID);


		//! Inicializa al tiempo especificado.
		//!
		//! @param time El tiempo, en cualquier unidad.
		void Initialize(unsigned long const & time);

		//! Actualiza el Scheduler, actualizando el tiempo y ejecutando todas
		//! aquellas tareas pendientes.
		//!
		//! @param delta Un incremento de tiempo, generalmente el incremento de
		//! tiempo pasado desde la última llamada a este mismo Update.
		//!
		//! @remark Una tarea no se ejecuta nunca más de una vez por ciclo (Update).
		//! En caso de que el delta exceda la frecuencia, la Tarea se ejecutará
		//! al siguiente ciclo, o a los siguientes, hasta llegar al número de veces
		//! apropiado.
		void Update(unsigned long const & delta);


		//! Ejecuta las tareas pendientes sin modificar el cronómetro interno.
		//!
		void RunPendingTasksOnly();


		//! Solamente actualiza el cronómetro interno mediante un incremento,
		//! sin ejecutar ninguna tarea pendiente.
		//!
		void UpdateOnly(unsigned long const & delta);

	};
