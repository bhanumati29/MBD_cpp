#include "Quaternion.h"

Quaternion::Quaternion(){
}

Quaternion::~Quaternion(){
}

double Quaternion::get_scalar(Quat q1) {
	return q1.q0;
}

Vect_3D Quaternion::get_vector(Quat q1){
	Vect_3D v(q1.q1, q1.q2, q1.q3);
	return v;
}

Quat Quaternion::identity() {
	Quat q3(1, 0, 0, 0);
	return q3;
}

Quat Quaternion::zeros() {
	Quat q3(0, 0, 0, 0);
	return q3;
}

Quat Quaternion::ones() {
	Quat q3(1, 1, 1, 1);
	return q3;
}

Quat Quaternion::add(Quat q1, Quat q2) {
	Quat q3(q1.q0 + q2.q0, q1.q1 + q2.q1, q1.q2 + q2.q2, q1.q3 + q2.q3);
	return q3;
}

Quat Quaternion::sub(Quat q1, Quat q2) {
	Quat q3(q1.q0 - q2.q0, q1.q1 - q2.q1, q1.q2 - q2.q2, q1.q3 - q2.q3);
	return q3;
}

Quat Quaternion::mul(Quat q1, Quat q2) {
	Quat q3;
	q3.q0 = q1.q0*q2.q0 - q1.q1*q2.q1 - q1.q2*q2.q2 - q1.q3*q2.q3;
	q3.q1 = q1.q0*q2.q1 + q1.q1*q2.q0 + q1.q2*q2.q3 - q1.q3*q2.q2;
	q3.q2 = q1.q0*q2.q2 - q1.q1*q2.q3 + q1.q2*q2.q0 + q1.q3*q2.q1;
	q3.q3 = q1.q0*q2.q3 + q1.q1*q2.q2 - q1.q2*q2.q1 + q1.q3*q2.q0;
	return q3;
}

Quat Quaternion::mul_scalar(Quat q1, double s) {
	Quat q2(q1.q0 * s, q1.q1 * s, q1.q2 * s, q1.q3 * s);
	return q2;
}

Quat Quaternion::mul_scalar(double s, Quat q1) {
	Quat q2(q1.q0 * s, q1.q1 * s, q1.q2 * s, q1.q3 * s);
	return q2;
}

Quat Quaternion::div_scalar(Quat q1, double s){
	Quat q2(q1.q0 / s, q1.q1 / s, q1.q2 / s, q1.q3 / s);
	return q2;
}

Quat Quaternion::div_scalar(double s, Quat q1) {
	Quat q2(q1.q0 / s, q1.q1 / s, q1.q2 / s, q1.q3 / s);
	return q2;
}

Quat Quaternion::conj(Quat q1) {
	Quat q2(q1.q0, -q1.q1, -q1.q2, -q1.q3);
	return q2;
}

double Quaternion::norm(Quat q1) {
	double l = sqrt(q1.q0 * q1.q0 + q1.q1 * q1.q1 + q1.q2 * q1.q2 + q1.q3 * q1.q3);
	return l;
}

Quat Quaternion::normalize(Quat q1) {
	double l = sqrt(q1.q0 * q1.q0 + q1.q1 * q1.q1 + q1.q2 * q1.q2 + q1.q3 * q1.q3);
	if (l == 0) {
		return q1;
	}
	else {
		Quat q2(q1.q0 / l, q1.q1 / l, q1.q2 / l, q1.q3 / l);
		return q2;
	}
}

Quat Quaternion::inv(Quat q1) {
	double l2 = q1.q0 * q1.q0 + q1.q1 * q1.q1 + q1.q2 * q1.q2 + q1.q3 * q1.q3;
	if (l2 == 1) {
		Quat q2(q1.q0, -q1.q1, -q1.q2, -q1.q3);
		return q2;
	}
	else {
		Quat q2(q1.q0 / l2, -q1.q1 / l2, -q1.q2 / l2, -q1.q3 / l2);
		return q2;
	}
}

Quat Quaternion::pow_scalar(Quat q, double r){
	double norm_q = norm(q);

	double th = acos(q.q0 / sqrt(q.q0 * q.q0 + q.q1 * q.q1 + q.q2 * q.q2 + q.q3 * q.q3));

	double u_norm = sqrt(q.q1 * q.q1 + q.q2 * q.q2 + q.q3 * q.q3);
	if(u_norm==0.0){
		double sin_r_th = sin(r * th);
		Quat q2(pow(norm_q,r), 0.0, 0.0, 0.0);
		return q2;
	}
	else{
		double u_hat_x = q.q1 / u_norm;
		double u_hat_y = q.q2 / u_norm;
		double u_hat_z = q.q3 / u_norm;

		double sin_r_th = sin(r * th);
		Quat q2(cos(r*th), u_hat_x * sin_r_th, u_hat_y * sin_r_th, u_hat_z * sin_r_th);
		q2 = mul_scalar(q2, pow(norm_q,r));

		return q2;
	}
}

Quat Quaternion::exp_quat(Quat q) {
	Quat q2;
	double u_norm = sqrt(q.q1 * q.q1 + q.q2 * q.q2 + q.q3 * q.q3);
	q2.q0 = cos(u_norm);

	q2.q1 = sin(u_norm) * q.q1 / u_norm;
	q2.q2 = sin(u_norm) * q.q2 / u_norm;
	q2.q3 = sin(u_norm) * q.q3 / u_norm;

	q2 = mul_scalar(q2, exp(q.q0));

	return q2;
}

Quat Quaternion::log_e(Quat q) {
	Quat q2;

	double q_norm = norm(q);
	q2.q0 = log(q_norm);

	double u_norm = sqrt(q.q1 * q.q1 + q.q2 * q.q2 + q.q3 * q.q3);
	double acos_q0_norm_q = acos(q.q0 / norm(q));
	q2.q1 = acos_q0_norm_q * q.q1 / u_norm;
	q2.q2 = acos_q0_norm_q * q.q2 / u_norm;
	q2.q3 = acos_q0_norm_q * q.q3 / u_norm;

	return q2;
}

Quat Quaternion::lerp(Quat q1, Quat q2, double tau){
	Quat ql;
	ql.q0 = (1.0 - tau)*q1.q0 + tau*q2.q0;
	ql.q1 = (1.0 - tau)*q1.q1 + tau*q2.q1;
	ql.q2 = (1.0 - tau)*q1.q2 + tau*q2.q2;
	ql.q3 = (1.0 - tau)*q1.q3 + tau*q2.q3;

	ql = normalize(ql);
	return ql;
}

Quat Quaternion::slerp(Quat q1, Quat q2, double tau){
	Quat qs;
	double dot = q1.q0*q2.q0 + q1.q1*q2.q1 + q1.q2*q2.q2 + q1.q3*q2.q3;
	if(dot<0.0){
		q2 = mul_scalar(q2, -1.0);
		dot = -1.0*dot;
	}
	if(dot>0.99995){
		qs = lerp(q1, q2, tau);
		return qs;
	}

	double th_0 = acos(dot);
	double s_th_0 = sin(th_0);

	
}

////////////////////////////////////////////////////////////

Diff::Diff() {
}

Diff::~Diff() {
}

Quat Diff::diff(Quat q_t, double dt) {
	Quat dq_dt = quat.div_scalar(quat.sub(q_t, q_t_1), dt);
	q_t_1 = q_t;
	return dq_dt;
}

void Diff::reset(){
	q_t_1 = quat.zeros();
}

////////////////////////////////////////////////////////////

Integrate::Integrate(){
}

Integrate::~Integrate(){
}

Quat Integrate::integrate(Quat q_t, double dt) {
	q_t_p_1 = quat.add(q_t_p_1, quat.mul_scalar(q_t, dt));
	return q_t_p_1;
}

void Integrate::reset() {
	q_t_p_1 = quat.zeros();
}