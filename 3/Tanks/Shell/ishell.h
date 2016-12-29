#pragma once

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>

class IShell : public QObject, public QGraphicsItem
{
	Q_OBJECT
public:
	virtual ~IShell();
	/**
	 * @brief getPoint Calculate shell's coordinates in passed moment of time
	 * @param time
	 * @return Point of the shell in passed moment of time
	 */
	virtual QPointF getPoint(double time) const;
	/**
	 * @return Angle of the shell in passed moment of time
	 */
	virtual double getAngle(double time) const;
	/**
	 * @brief shoot Shoots with passed impuls
	 */
	virtual void shoot(double impuls);
	/**
	 * @brief cancelShoot Terminates shot
	 */
	virtual void cancelShoot();
	/**
	 * @brief showCursor Show cursor on the scene that moving for shell by x-coordinate
	 */
	virtual void showCursor() = 0;
	virtual void hideCursor() = 0;
	virtual double getExplosiveRadius() = 0;
	virtual void explode() = 0;

	enum class Type
	{
		simple,
		explosive
	};

signals:
	void updatingPos();

protected:
	IShell(double x, double y, double angle, QObject *parent = 0);
	virtual double getWeight() = 0;
	virtual QGraphicsItem *getCursor() const = 0;

protected slots:
	/**
	 * @brief updatePos Updating shell's coordinates according to time
	 */
	virtual void updatePos();

private:
	const double g = 9.8;
	double speed = 0;
	double startX = 0;
	double startY = 0;
	double startAngle = 0;
	double time = 0;
	int fps = 60;
	double dt = 3.0 / fps;
	QTimer timer;
};
